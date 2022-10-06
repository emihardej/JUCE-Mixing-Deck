/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 2 Aug 2021 2:59:42pm
    Author:  Emi

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class DJAudioPlayer : public juce::AudioSource {
    public:

        DJAudioPlayer(juce::AudioFormatManager& _formatManager);
        ~DJAudioPlayer();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

        void loadURL(juce::URL audioURL);
        void setGain(double gain);
        void setSpeed(double ratio);
        void setPosition(double posInSecs);
        void setPositionRelative(double pos);

        void start();
        void stop();
        void isLooping();

        //get the relative position of the playhead
        double getPositionRelative();

    private:
        juce::AudioFormatManager& formatManager;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::AudioTransportSource transportSource;
        juce::ResamplingAudioSource resampleSource{ &transportSource,false,2 };
};