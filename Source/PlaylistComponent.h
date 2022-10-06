/*
  ==============================================================================

    PlaylistComponent.h
    Created: 19 Aug 2021 10:42:34am
    Author:  Emi

  ==============================================================================
*/

#pragma once
#include <vector>
#include <array>
#include <string>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class PlaylistComponent : public juce::Component,
    public juce::TableListBoxModel,
    public juce::Button::Listener
    
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows () override;

    void paintRowBackground (juce::Graphics &, int rowNumber,
                             int width, int height, 
                             bool rowIsSelected) override;

    void paintCell (juce::Graphics &, int rowNumber,
                    int columnId, int width,
                    int height, bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber, 
                                       int columnId,
                                       bool isRowSelected, 
                                       Component* existingComponentToUpdate) override;

    void loadToTable(juce::URL audioFile);

    void buttonClicked(juce::Button* button) override;


private:
    
    juce::TableListBox tableComponent;
    std::vector<juce::String> trackTitles;
    std::vector<juce::File> file;
    juce::TextButton loadButton{ "LOAD TRACK" };
    juce::TextButton player1Button{ "Play on Deck 1" };
    juce::TextButton player2Button{ "Play on Deck 2" };
    //DJAudioPlayer* player;
    juce::AudioFormatManager formatManager;
    DJAudioPlayer player1{ formatManager };
    DJAudioPlayer player2{ formatManager };
    juce::ModifierKeys modifier;
    //WaveformDisplay waveformDisplay;
  
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
