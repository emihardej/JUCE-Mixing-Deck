/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 19 Aug 2021 10:42:34am
    Author:  Emi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    tableComponent.getHeader().addColumn("Track Title", 1, 400);
    tableComponent.getHeader().addColumn(" ", 2, 200);
    tableComponent.getHeader().addColumn(" ", 3, 200);
    //tableComponent.getHeader().addColumn("Add Track", 3, 200);
    

    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);



}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    double rowH = getHeight() / 9;
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
    loadButton.setBounds(0, rowH * 6, getWidth(), rowH);
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::turquoise);
    }
    else {
        g.fillAll(juce::Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (columnId == 1)
    {
        g.drawText(trackTitles[rowNumber],
            2, 0,
            width - 4, height,
            juce::Justification::centredLeft, true);
    }
    
}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {

        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{ "Play" };
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

//R3A When column clicked the file browser will open and load the file chosen in the directory
void PlaylistComponent::buttonClicked(juce::Button* button)
{
    //juce::Array<juce::URL> file;
    //if (button == &loadButton) {
    //    juce::FileChooser chooser{ "Select an mp3 files.." };
    //    if (chooser.browseForFileToOpen())
    //        {
    //        loadToTable(juce::URL{ chooser.getResult() });
    //        //waveformDisplay.loadURL(juce::URL{ chooser.getResult() });
    //        //player->loadURL(juce::URL{ chooser.getResult() });
    //        //player->loadURL(file[std::stoi(button->getComponentID().toStdString())]); // your player
    //        //loadToTable(file[std::stoi(button->getComponentID().toStdString())]); // your table
    //        //player->start();
    //        }
    //    
    //}
}

void PlaylistComponent::loadToTable(juce::URL audioFile)
{
    for (auto i : trackTitles)
    {
        trackTitles.push_back(audioFile.getFileName());

    }
    tableComponent.updateContent();
}

//R3A When column clicked the file browser will open and load the file chosen in the directory
//void PlaylistComponent::columnClicked(int columnId, const ModifierKeys& mods)
//{
//    //if left mouse button down
//    if (mods == modifier.isLeftButtonDown())
//    {
//        //column 3 = 'add track' cells. may change to a button
//        if (columnId == 3)
//        {
//            FileChooser chooser{ "Select a file" };
//            if (chooser.browseForFileToOpen())
//            {
//                //selected file 
//                player->loadURL(URL{ chooser.getResult() }); //move this to isSelected?
//                waveformDisplay.loadURL(URL{ chooser.getResult() });
//            }
//        }
//    }
//}



