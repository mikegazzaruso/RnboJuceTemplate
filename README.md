# RnboJuceTemplate
A JUCE Template for a minimal Synth that encapsulates rnboObject's data into modern JUCE APVTS approach

## How it works
Inside the "Juce Project" folder you will find the actual JUCE Project, with Max code already exported as C++ code and placed inside the "Export" directory.
<br><br>Inside the "Max" folder you will find the actual Max and rnbo~ project files for the minimal synthesizer. It's a polyphonic (16 voices) synth with a single VCO (sine wave), no VCF and a standard ADSR VCA.

## Why this is different from Cyclying '74 standard RNBOJUCE Template
This use APVTS in order to hook your processor's parameter to rnboObject's internal state. This is more convenient and modern approach for writing JUCE plugins.

## GenericAudioProcessorEditor is used, what if I would implement custom GUI? 
In PluginProcessor.cpp, change line 294 to<br>
return new RnboJuceTemplateAudioProcessorEditor (*this);

<br>and implement your custom GUI

### Instructions
1. Inside Projucer project, be sure to set properly your header search paths accordingly 
/Users/<your_user>/<your_project_dir>/Juce Project/Export/rnbo<br>
/Users/<your_user>/<your_project_dir>/Juce Project/Export/rnbo/common

2. Compile as VST3 and/or AU

3. Launch your DAW

4. Enjoy


