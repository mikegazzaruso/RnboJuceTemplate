/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RNBO.h"
#include "RNBO_TimeConverter.h"

//==============================================================================
/**
*/
class RnboJuceTemplateAudioProcessor  : public juce::AudioProcessor,
                                        public juce::AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    RnboJuceTemplateAudioProcessor();
    ~RnboJuceTemplateAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void parameterChanged (const juce::String& parameterID, float newValue) override;

private:
    AudioProcessorValueTreeState apvts;
    UndoManager undoManager;
    
    double _lastBPM = -1.0;
    int _lastTimeSigNumerator = 0;
    int _lastTimeSigDenominator = 0;
    double _lastPpqPosition = -1.0;
    bool _lastIsPlaying = false;
    
    RNBO::CoreObject rnboObject;
    
    RNBO::MidiEventList _midiInput;
    RNBO::MidiEventList _midiOutput;
    
    void wrapProcess(size_t numSamples, juce::MidiBuffer& midiMessages, std::function<void(void)> process);
    
    std::unordered_map<juce::String, RNBO::ParameterIndex> apvtsParamIdToRnboParamIndex;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RnboJuceTemplateAudioProcessor)
};
