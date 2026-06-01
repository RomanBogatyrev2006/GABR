#pragma once

#include <soloud.h>
#include <soloud_wav.h>
#include <soloud_wavstream.h>

namespace Gabr
{
	class AudioManager;

	struct VoiceHandle
	{
		uint32_t id = 0;
		uint32_t generation = 0;

		class Voice* Get() const;
		bool IsValid() const { return manager != nullptr; }

	private:
		AudioManager* manager = nullptr;
		friend class AudioManager;
	};

	class Voice
	{
	public:
		void Play();
		void Stop();
		void Pause(bool pause);

		void Set(const std::string& tag, bool stream);

		void SetVolume(float v);
		float GetVolume() const;

		void SetPitch(float p);
		float GetPitch() const;

		void SetPan(float p);
		float GetPan() const;

		void SetLooping(bool loop);
		void SetLoopPoint(double seconds);
		double GetLoopPoint() const;

		void SetPriority(int p);
		int GetPriority() const;

		void SetSelfDestroy(bool v);
		bool IsSelfDestroy() const;

		bool IsStream() const;

	private:
		friend class AudioManager;

		SoLoud::handle handle = 0;

		std::string tag;
		bool stream = false;

		float volume = 1.0f;
		float pitch = 1.0f;
		float pan = 0.0f;
		bool looping = false;
		double loopPoint = 0.0;

		int priority = 0;
		bool selfDestroy = true;

		AudioManager* manager = nullptr;
	};

	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		void Update();

		// Voices
		VoiceHandle CreateVoice(
			const std::string& tag = "",
			bool stream = false,
			float volume = 1.0f,
			float pitch = 1.0f,
			float pan = 0.0f,
			bool loop = false,
			int priority = 0
		);

		void DestroyVoice(VoiceHandle handle);

		// Sounds
		bool LoadSound(const std::string& path);
		void UnloadSound(const std::string& tag);

		bool LoadStream(const std::string& path);
		void UnloadStream(const std::string& tag);

		Voice* Get(VoiceHandle handle);
		bool IsAlive(VoiceHandle handle) const;

	private:
		friend class Voice;

		std::string MakeTag(const std::string& path);

		bool CanPlay(int priority);

		SoLoud::Soloud engine;

		std::unordered_map<std::string, std::unique_ptr<SoLoud::Wav>> sounds;
		std::unordered_map<std::string, std::unique_ptr<SoLoud::WavStream>> streams;

		// voices storage
		std::vector<std::unique_ptr<Voice>> voices;
		std::vector<uint32_t> generations;
		std::vector<uint32_t> freeIds;

		const uint32_t maxVoices = 32;
	};
}