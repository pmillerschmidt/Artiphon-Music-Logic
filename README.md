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

Here are a few examples of the generator creating top-line melodies. The drum/bass/chords are just for reference, the lead melody is the generated section. (mp4 for gh support)

https://github.com/user-attachments/assets/f1a541f1-c079-42c0-b2dd-117ceea32305

https://github.com/user-attachments/assets/e7aa5f13-45b7-4cd8-aeb6-128ef7e08b78

https://github.com/user-attachments/assets/2b5cf8b2-19ac-4d47-87ce-f413f9572861


