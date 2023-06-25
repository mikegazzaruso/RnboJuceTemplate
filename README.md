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
<br>and implement your custom GUI.

### How to use RnboJuceTemplate?
1. Inside Projucer project, be sure to set properly your header search paths accordingly 
<br>`/Users/<your_user>/<your_project_dir>/Juce Project/Export/rnbo`<br>
`/Users/<your_user>/<your_project_dir>/Juce Project/Export/rnbo/common`

2. Compile as `VST3` and/or `AU`

3. Launch your `DAW`

4. Enjoy

<h2>Max Patcher</h2>
<img width="891" alt="Screenshot 2023-06-25 alle 20 33 00" src="https://github.com/mikegazzaruso/RnboJuceTemplate/assets/9842486/10cf1b64-42c7-4820-a5bb-19db3da74d21">

<br>
<h2>rnbo~ Patcher</h2>
<img width="863" alt="Screenshot 2023-06-25 alle 20 33 09" src="https://github.com/mikegazzaruso/RnboJuceTemplate/assets/9842486/684835cb-0c90-440d-8f90-a471732e2232">

<br>
<h2>Plugin inside Ableton Live 11 (VST3)</h2>
<img width="1206" alt="Screenshot 2023-06-25 alle 20 33 32" src="https://github.com/mikegazzaruso/RnboJuceTemplate/assets/9842486/994a589e-6e7d-4e71-be51-3044250c4369">

