#include "AudioManager.h"

namespace Gabr
{
	Voice* VoiceHandle::Get() const
	{
		if (!manager) return nullptr;
		return manager->Get(*this);
	}

	AudioManager::AudioManager()
	{
		engine.init();
	}

	AudioManager::~AudioManager()
	{
		engine.deinit();
	}

	void AudioManager::Update()
	{
		for (uint32_t i = 0; i < voices.size(); i++)
		{
			auto& v = voices[i];
			if (!v) continue;

			if (v->selfDestroy)
			{
				if (!engine.isValidVoiceHandle(v->handle))
				{
					VoiceHandle h;
					h.id = i;
					h.generation = generations[i];
					h.manager = this;

					DestroyVoice(h);
				}
			}
		}
	}

	std::string AudioManager::MakeTag(const std::string& path)
	{
		return path;
	}

	bool AudioManager::LoadSound(const std::string& path)
	{
		std::string tag = MakeTag(path);

		auto wav = std::make_unique<SoLoud::Wav>();
		if (wav->load(path.c_str()) != SoLoud::SO_NO_ERROR)
			return false;

		sounds[tag] = std::move(wav);
		return true;
	}

	void AudioManager::UnloadSound(const std::string& tag)
	{
		sounds.erase(tag);
	}

	bool AudioManager::LoadStream(const std::string& path)
	{
		std::string tag = MakeTag(path);

		auto wav = std::make_unique<SoLoud::WavStream>();
		if (wav->load(path.c_str()) != SoLoud::SO_NO_ERROR)
			return false;

		streams[tag] = std::move(wav);
		return true;
	}

	void AudioManager::UnloadStream(const std::string& tag)
	{
		streams.erase(tag);
	}

	bool AudioManager::CanPlay(int priority)
	{
		int active = engine.getActiveVoiceCount();

		if (active < (int)maxVoices)
			return true;

		int lowest = priority;

		for (auto& v : voices)
		{
			if (!v) continue;
			lowest = min(lowest, v->priority);
		}

		return priority >= lowest;
	}

	VoiceHandle AudioManager::CreateVoice(
		const std::string& tag,
		bool stream,
		float volume,
		float pitch,
		float pan,
		bool loop,
		int priority
	)
	{
		uint32_t id;

		if (!freeIds.empty())
		{
			id = freeIds.back();
			freeIds.pop_back();
		}
		else
		{
			id = (uint32_t)voices.size();
			voices.emplace_back(nullptr);
			generations.push_back(0);
		}

		auto voice = std::make_unique<Voice>();
		voice->manager = this;

		voice->volume = volume;
		voice->pitch = pitch;
		voice->pan = pan;
		voice->looping = loop;
		voice->priority = priority;
		voice->tag = tag;
		voice->stream = stream;

		SoLoud::handle h = 0;

		// -----------------------------
		// TRY PLAY
		// -----------------------------
		if (!tag.empty())
		{
			if (stream)
			{
				auto it = streams.find(tag);
				if (it != streams.end())
					h = engine.play(*it->second);
			}
			else
			{
				auto it = sounds.find(tag);
				if (it != sounds.end())
					h = engine.play(*it->second);
			}
		}

		// -----------------------------
		// NO SLOT? TRY STEAL
		// -----------------------------
		if (!engine.isValidVoiceHandle(h))
		{
			int victimId = FindLowestPriorityVoice();

			if (victimId != -1)
			{
				auto& victim = voices[victimId];

				if (victim && victim->priority < priority)
				{
					if (engine.isValidVoiceHandle(victim->handle))
						engine.stop(victim->handle);

					victim.reset();
					generations[victimId]++;
					freeIds.push_back(victimId);

					if (stream)
					{
						auto it = streams.find(tag);
						if (it != streams.end())
							h = engine.play(*it->second);
					}
					else
					{
						auto it = sounds.find(tag);
						if (it != sounds.end())
							h = engine.play(*it->second);
					}
				}
			}
		}

		voice->handle = h;

		// -----------------------------
		// APPLY PARAMS
		// -----------------------------
		if (engine.isValidVoiceHandle(h))
		{
			engine.setVolume(h, volume);
			engine.setPan(h, pan);
			engine.setRelativePlaySpeed(h, pitch);
			engine.setLooping(h, loop);
		}

		voices[id] = std::move(voice);

		VoiceHandle out;
		out.id = id;
		out.generation = generations[id];
		out.manager = this;

		return out;
	}

	void AudioManager::DestroyVoice(VoiceHandle handle)
	{
		if (!IsAlive(handle)) return;

		auto& v = voices[handle.id];

		if (engine.isValidVoiceHandle(v->handle))
			engine.stop(v->handle);

		v.reset();
		generations[handle.id]++;
		freeIds.push_back(handle.id);
	}

	Voice* AudioManager::Get(VoiceHandle handle)
	{
		if (!IsAlive(handle)) return nullptr;
		return voices[handle.id].get();
	}

	bool AudioManager::IsAlive(VoiceHandle handle) const
	{
		return handle.manager == this &&
			handle.id < voices.size() &&
			generations[handle.id] == handle.generation &&
			voices[handle.id] != nullptr;
	}

	void Voice::Play()
	{
		if (!manager) return;

		Stop();

		if (stream)
		{
			auto it = manager->streams.find(tag);
			if (it != manager->streams.end())
				handle = manager->engine.play(*it->second);
		}
		else
		{
			auto it = manager->sounds.find(tag);
			if (it != manager->sounds.end())
				handle = manager->engine.play(*it->second);
		}

		if (manager->engine.isValidVoiceHandle(handle))
		{
			manager->engine.setVolume(handle, volume);
			manager->engine.setPan(handle, pan);
			manager->engine.setRelativePlaySpeed(handle, pitch);
			manager->engine.setLooping(handle, looping);

			if (loopPoint > 0.0)
				manager->engine.setLoopPoint(handle, loopPoint);
		}
	}

	void Voice::Stop()
	{
		if (manager && manager->engine.isValidVoiceHandle(handle))
			manager->engine.stop(handle);
	}

	void Voice::Pause(bool pause)
	{
		if (manager && manager->engine.isValidVoiceHandle(handle))
			manager->engine.setPause(handle, pause);
	}

	void Voice::Set(const std::string& t, bool s)
	{
		tag = t;
		stream = s;

		Play();
	}

	void Voice::SetVolume(float v)
	{
		volume = v;

		if (manager && manager->engine.isValidVoiceHandle(handle))
			manager->engine.setVolume(handle, v);
	}

	float Voice::GetVolume() const { return volume; }

	void Voice::SetPitch(float p)
	{
		pitch = p;

		if (manager && manager->engine.isValidVoiceHandle(handle))
			manager->engine.setRelativePlaySpeed(handle, p);
	}

	float Voice::GetPitch() const { return pitch; }

	void Voice::SetPan(float p)
	{
		pan = p;

		if (manager && manager->engine.isValidVoiceHandle(handle))
			manager->engine.setPan(handle, p);
	}

	float Voice::GetPan() const { return pan; }

	void Voice::SetLooping(bool loop)
	{
		looping = loop;

		if (manager && manager->engine.isValidVoiceHandle(handle))
			manager->engine.setLooping(handle, loop);
	}

	void Voice::SetLoopPoint(double s)
	{
		loopPoint = s;

		if (manager && manager->engine.isValidVoiceHandle(handle))
			manager->engine.setLoopPoint(handle, s);
	}

	double Voice::GetLoopPoint() const { return loopPoint; }

	void Voice::SetPriority(int p) { priority = p; }
	int Voice::GetPriority() const { return priority; }

	void Voice::SetSelfDestroy(bool v) { selfDestroy = v; }
	bool Voice::IsSelfDestroy() const { return selfDestroy; }

	bool Voice::IsStream() const { return stream; }

	int AudioManager::FindLowestPriorityVoice()
	{
		int lowestIndex = -1;
		int lowestPriority = INT_MAX;

		for (int i = 0; i < (int)voices.size(); i++)
		{
			auto& v = voices[i];
			if (!v) continue;
			if (!engine.isValidVoiceHandle(v->handle)) continue;

			if (v->priority < lowestPriority)
			{
				lowestPriority = v->priority;
				lowestIndex = i;
			}
		}

		return lowestIndex;
	}
}