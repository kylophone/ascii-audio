/** \brief Fill a 5 byte array with the memory needed to display low resolution (7x5) ASCII characters. Uses the TI-83 font.
* @param this_letter character to be converted.
* @param mem_array display memory. Allocate 5 bytes.
* http://tibasicdev.wikidot.com/83lgfont
*/
int ti83font(char this_ascii, char *mem_array);
