/*
  ==============================================================================

    DeckGUI.cpp
    Created: 3 Aug 2021 11:08:30am
    Author:  Emi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"


//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
    juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse
                ) : player(_player),
                    waveformDisplay(formatManagerToUse, cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(loopButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    loopButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 20);
    speedSlider.setRange(0.0, 100.0);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    speedSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 20);
    posSlider.setRange(0.0, 1.0);
    posSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    posSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 20);

    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::black);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    //g.drawText ("DeckGUI", getLocalBounds(),
    //    juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    DBG(" MainComponent::buttonClicked: A button has been clicked");
    if (button == &playButton) // clicked button has same memory address as playButton
    {
        DBG(" MainComponent::buttonClicked: playButton");
        player->start();
    }
    if (button == &stopButton)
    {
        DBG(" MainComponent::buttonClicked: stopButton");
        player->stop();
    }
    if (button == &loadButton) {
        juce::Array<juce::URL> file;
        juce::FileChooser chooser{ "Select an mp3 files.." };
        if (chooser.browseForFileToOpen())
        {
            playlist.loadToTable(juce::URL{ chooser.getResult() });
            waveformDisplay.loadURL(juce::URL{ chooser.getResult() });
            player->loadURL(juce::URL{ chooser.getResult() });
            //playlist.loadToTable(file[std::stol(button->getComponentID().toStdString())]); // your table
        }

    }
    if (button == &loopButton)
    {
        DBG(" MainComponent::buttonClicked: loopButton");
        player->isLooping();
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}
void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight() / 9;
    double rowW = getWidth() / 4;

    playButton.setBounds(0, 0, getWidth()/2, rowH);
    stopButton.setBounds(getWidth()/2, 0, getWidth()/2, rowH);
    loopButton.setBounds(0, rowH, getWidth(), rowH);
    volSlider.setBounds(0, rowH * 2, rowW, rowH*2);
    speedSlider.setBounds(rowW, rowH * 2, rowW*2, rowH*2);
    posSlider.setBounds(rowW*2, rowH * 2, rowW*3, rowH * 2);

    waveformDisplay.setBounds(0, rowH * 4, getWidth(), rowH * 2);

    loadButton.setBounds(0, rowH * 6, getWidth(), rowH);
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (juce::String filename : files)
    {
        DBG("DeckGUI::filesDropped " << filename);
        juce::URL fileURL = juce::URL{ juce::File{filename} };
        waveformDisplay.loadURL(juce::URL{ filename });
        playlist.loadToTable(fileURL);
        player->loadURL(fileURL);
        return;
    }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}
