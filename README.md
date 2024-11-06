# Context-Sensitive Melody Generator

For my capstone, music logic project at Artiphon, I built a context-sensitive, Markov-based melody generator in C++. The algorithm incorporated a Trigram Hidden Markov Model
and user-specified hyper-parameters for precise melodic control. The program parses artist-specific MIDI to emulate their style. For my exploration, I fed it Avicii top-line melodies normalized around A minor. The model is designed to be lightweight and work on the low-memory, embedded systems that Artiphon specializes in. 

### Hyper-parameters
  1. chord coefficient: the likelihood of chord tones
  2. strong note coefficient: the likelihood that down beats emphasize chord tones
  3. movement hesitance: the amount of desired movement (jumpiness)
  4. movement spread: essentially the range of the generated melody
  5. repetition coefficient: likelihood of repetition (1 = none, 0 = total repetition)

### Examples

Here are a few examples of the generator creating top-line melodies. The hyperparameters are displayed in the title. The drum/bass/chords are just for reference, the lead melody is the generated section. (mp4 for github support)




https://github.com/user-attachments/assets/584fddd2-8bbf-4b21-aca3-8a96e66fbda7


https://github.com/user-attachments/assets/ba0f4c35-9e25-40f2-a80e-588dee13046c


https://github.com/user-attachments/assets/6c22362e-0645-4df1-bf5e-a509e91b17ed

