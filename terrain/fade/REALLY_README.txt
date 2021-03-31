IMPORTANT INFORMATIONS
======================

1. UPGRADES FROM A PREVIOUS VERSION: 

- When you upgrade from a previous Fade version, you *also* need 
to replace the header files.

- Recent change: To avoid passing std::strings over the DLL 
boundary, some parameters have been changed from std::string 
to const char*. You will often not even notice this, but if 
your existing code does not compile anymore, then this is the 
reason. Then please pass "yourString" as "yourString.c_str()" 
to resolve that. This change was unavoidable. Thank you for 
your understanding.



2. TROUBLESHOOTING

+ Linux/Apple-Users: You need libgmp and you must activate the 
line with your OS in the Makefile. 


Have much success!

