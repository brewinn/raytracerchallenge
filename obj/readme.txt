This directory (obj/) holds compiled object files from make. This allows make
to only recompile the files that have changed since the last compilation. Any
object file here may be deleted either directly, or through the use of 'make
cleanall' in one of the directories with a Makefile.
