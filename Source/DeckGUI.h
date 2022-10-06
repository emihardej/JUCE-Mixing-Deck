/*
  ==============================================================================

    DeckGUI.h
    Created: 3 Aug 2021 11:08:30am
    Author:  Emi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaylistComponent.h"


//==============================================================================
/*
*/
class DeckGUI : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget,
                public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    void timerCallback() override;
    
private:

    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton loadButton{ "LOAD" };
    juce::ToggleButton loopButton{ "LOOP" };
    juce::Slider volSlider{ "VOLUME" };
    juce::Slider speedSlider{ "PLAYBACK SPEED" };
    juce::Slider posSlider{ "TIME" };

    PlaylistComponent playlist;
    DJAudioPlayer* player;
    WaveformDisplay waveformDisplay;

    juce::File file;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
