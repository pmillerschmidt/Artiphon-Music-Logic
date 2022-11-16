std::vector<int> cacheMelody(std::vector<Melody>& melody, int tpq);
//////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
   checkOptions(options, argc, argv);
   MidiFile midifile(options.getArg(1));
   if (options.getBoolean("track-count")) {
      cout << midifile.getTrackCount() << endl;
      return 0;
   }
   if (!options.getBoolean("track")) {
      midifile.joinTracks();
   } 

   vector<Melody> melody;
   convertToMelody(midifile, melody);
   sortMelody(melody);

   //make MM
   MM verse_mm;
   // verse_mm.update(60, 67, 1);
   // int note = verse_mm.next(60);

   std::vector<int> melody_tones = cacheMelody(melody, midifile.getTicksPerQuarterNote());
   verse_mm.update_line(melody_tones);
   int note = verse_mm.next(81);
   // printMelody(melody, midifile.getTicksPerQuarterNote());
   cout << note << "\n";
   return 0;
}

//cache melody
std::vector<int> cacheMelody(std::vector<Melody>& melody, int tpq) {
   std::vector<int> out;
   if (melody.size() < 1) {
      return {0};
   }
   Melody temp;
   temp.tick = melody[melody.size()-1].tick +
               melody[melody.size()-1].duration;
   temp.pitch = 0;
   temp.duration = 0;
   melody.push_back(temp);

   for (int i=0; i<(int)melody.size()-1; i++) {
      double delta = melody[i+1].tick - melody[i].tick;
      if (delta == 0) {
         continue;
      }
      // cout << melody[i].pitch << "\n";
      out.push_back(melody[i].pitch);

   }
   return out;

}