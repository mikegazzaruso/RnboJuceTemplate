# RnboJuceTemplate
A [JUCE](https://juce.com) Template including a minimal synthesizer created with MaxMSP's [rnbo~](https://rnbo.cycling74.com/), that encapsulates rnboObject's state into JUCE's AudioProcessor using modern JUCE APVTS fashion.

## How it works
Inside the `Juce Project` folder you will find the actual JUCE Project, with Max code already exported as C++ code and placed inside the `Export` folder.
<br><br>Inside the `Max` folder you will find the actual `Max` and `rnbo~` project files for the minimal synthesizer. It's a polyphonic (16 voices) synth with a single VCO (sine wave), no VCF and a standard ADSR VCA.

## How does it differ from Cyclying '74 standard RNBOJUCE Template?
This Template uses [APVTS](https://docs.juce.com/master/tutorial_audio_processor_value_tree_state.html) approach in order to hook your processor's parameter to rnboObject's internal state. This is more convenient and modern approach for writing JUCE plugins.

## GenericAudioProcessorEditor is used, what if I would implement custom GUI? 
In `PluginProcessor.cpp`, change line 294 to<br>
`return new RnboJuceTemplateAudioProcessorEditor (*this);`

<br>and implement your custom GUI

### Instructions
1. Inside Projucer project, be sure to set properly your header search paths accordingly 
<br>`/Users/<your_user>/<your_project_dir>/Juce Project/Export/rnbo`<br>
`/Users/<your_user>/<your_project_dir>/Juce Project/Export/rnbo/common`

2. Compile as `VST3` and/or `AU`

3. Launch your `DAW`

4. Enjoy


