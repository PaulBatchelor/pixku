# Spigot Test

This short test program runs Spigot code inside of Pixku.

To generate the audio file, run "make". This will use Spigot's tracker 
interface to sequence an FM tone using the note information in "notes.rnt".

To run the Spigot GUI, use the "gui.sp" file with Spigot with "spigot gui.sp".
While there is some duplicate code, both versions of the patch share the 
polysporth file sine.scm. 
