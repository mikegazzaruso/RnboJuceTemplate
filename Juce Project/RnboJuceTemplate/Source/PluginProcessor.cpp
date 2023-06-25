/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParamIds.h"

static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::attack, 1 },
                                                             "attack",
                                                             juce::NormalisableRange<float> (0.1f, 2000.0f, 0.01f, 1.f),
                                                             0.1f,
                                                             juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             nullptr,
                                                             nullptr));
    
    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::decay, 1 },
                                                             "decay",
                                                             juce::NormalisableRange<float> (0.1f, 2000.0f, 0.01f, 1.f),
                                                             0.1f,
                                                             juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             nullptr,
                                                             nullptr));
    
    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::sustain, 1 },
                                                             "sustain",
                                                             juce::NormalisableRange<float> (0.1f, 1.f, 0.01f, 1.f),
                                                             1.f,
                                                             juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             nullptr,
                                                             nullptr));
    
    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::release, 1 },
                                                             "release",
                                                             juce::NormalisableRange<float> (0.1f, 2000.0f, 0.01f, 1.f),
                                                             0.1f,
                                                             juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             nullptr,
                                                             nullptr));


    return layout;
}


//==============================================================================
RnboJuceTemplateAudioProcessor::RnboJuceTemplateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    apvts (*this, &undoManager, "Parameters", createParameterLayout())
{
    for (RNBO::ParameterIndex i = 0; i < rnboObject.getNumParameters(); ++i)
        {
            RNBO::ParameterInfo info;
            rnboObject.getParameterInfo (i, &info);
            auto paramID = juce::String (rnboObject.getParameterId (i));
            DBG(paramID);
            
            if (info.visible)
            {
                auto paramID = juce::String (rnboObject.getParameterId (i));

                // Each apvts parameter id and range must be the same as the rnbo param object's.
                // If you hit this assertion then you need to fix the incorrect id in ParamIDs.h.
                jassert (apvts.getParameter (paramID) != nullptr);

                // If you hit these assertions then you need to fix the incorrect apvts
                // parameter range in createParameterLayout().
                // jassert (info.min == apvts.getParameterRange (paramID).start);
                // jassert (info.max == apvts.getParameterRange (paramID).end);

                apvtsParamIdToRnboParamIndex[paramID] = i;

                apvts.addParameterListener (paramID, this);
                rnboObject.setParameterValue (i, apvts.getRawParameterValue (paramID)->load());
            }
        }
}

RnboJuceTemplateAudioProcessor::~RnboJuceTemplateAudioProcessor()
{
}

//==============================================================================
const juce::String RnboJuceTemplateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RnboJuceTemplateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RnboJuceTemplateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RnboJuceTemplateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RnboJuceTemplateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RnboJuceTemplateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RnboJuceTemplateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RnboJuceTemplateAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RnboJuceTemplateAudioProcessor::getProgramName (int index)
{
    return {};
}

void RnboJuceTemplateAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void RnboJuceTemplateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    rnboObject.prepareToProcess (sampleRate, static_cast<size_t> (samplesPerBlock));
}

void RnboJuceTemplateAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RnboJuceTemplateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void RnboJuceTemplateAudioProcessor::wrapProcess(size_t numSamples, juce::MidiBuffer& midiMessages, std::function<void(void)> process) {
    RNBO::MillisecondTime time = rnboObject.getCurrentTime();

    //transport
    {
        AudioPlayHead* playhead = getPlayHead();
        if (playhead) {
            auto info = playhead->getPosition();
            if (info) {
                auto bpm = info->getBpm();
                if (bpm && *bpm != _lastBPM) {
                    _lastBPM = *bpm;
                    RNBO::TempoEvent event(time, _lastBPM);
                    rnboObject.scheduleEvent(event);
                }

                auto timesig = info->getTimeSignature();
                if (timesig && (timesig->numerator != _lastTimeSigNumerator || timesig->denominator != _lastTimeSigDenominator)) {
                    _lastTimeSigNumerator = timesig->numerator;
                    _lastTimeSigDenominator = timesig->denominator;
                    RNBO::TimeSignatureEvent event(time, _lastTimeSigNumerator, _lastTimeSigDenominator);
                    rnboObject.scheduleEvent(event);
                }

                auto ppqPos = info->getPpqPosition();
                if (ppqPos && *ppqPos != _lastPpqPosition) {
                    _lastPpqPosition = *ppqPos;
                    RNBO::BeatTimeEvent event(time, _lastPpqPosition);
                    rnboObject.scheduleEvent(event);
                }

                auto playing = info->getIsPlaying();
                if (playing != _lastIsPlaying) {
                    _lastIsPlaying = playing;
                    RNBO::TransportEvent event(time, _lastIsPlaying ? RNBO::TransportState::RUNNING : RNBO::TransportState::STOPPED);
                    rnboObject.scheduleEvent(event);
                }
            }
        }
    }

    // fill midi input
    RNBO::TimeConverter timeConverter(rnboObject.getSampleRate(), time);

    _midiInput.clear();  // make sure midi input starts clear
    for (auto meta: midiMessages)
    {
        RNBO::MillisecondTime t = timeConverter.convertSampleOffsetToMilliseconds(meta.samplePosition);
        _midiInput.addEvent(RNBO::MidiEvent(t, 0, meta.data, (size_t)meta.numBytes));
    }

    process();

    // consume midi output
    midiMessages.clear();        // clear the input that we consumed above so juce doesn't get confused
    if (!_midiOutput.empty()) {
        std::for_each(_midiOutput.begin(),
                      _midiOutput.end(),
                      [&timeConverter, &midiMessages](const RNBO::MidiEvent& ev) {
                          int sampleNumber = static_cast<int>(timeConverter.convertMillisecondsToSampleOffset(ev.getTime()));
                          auto midiMessage = MidiMessage(ev.getData(), (int)ev.getLength());
                          midiMessages.addEvent(midiMessage, sampleNumber);
                      });
        _midiOutput.clear();
    }
}

void RnboJuceTemplateAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto samples = static_cast<size_t>(buffer.getNumSamples());
    wrapProcess(samples, midiMessages, [this, samples, &buffer]() {
            rnboObject.process(
                    buffer.getArrayOfReadPointers(), static_cast<size_t>(buffer.getNumChannels()),
                    buffer.getArrayOfWritePointers(), static_cast<size_t>(buffer.getNumChannels()),
                    samples,
                    &_midiInput, &_midiOutput
                    );
            }
    );
}

//==============================================================================
bool RnboJuceTemplateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* RnboJuceTemplateAudioProcessor::createEditor()
{
    // return new RnboJuceTemplateAudioProcessorEditor (*this);
    return new GenericAudioProcessorEditor (*this);
}

//==============================================================================
void RnboJuceTemplateAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos (destData, true);
        apvts.state.writeToStream (mos);
}

void RnboJuceTemplateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData (data, static_cast<size_t> (sizeInBytes));

       if (tree.isValid())
           apvts.replaceState (tree);
}

void RnboJuceTemplateAudioProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    rnboObject.setParameterValue (apvtsParamIdToRnboParamIndex[parameterID], newValue);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RnboJuceTemplateAudioProcessor();
}
