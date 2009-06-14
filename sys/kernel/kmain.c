int kmain() {
	// String zum Ausgeben
	char *hello = "Hello World";
 
	con_clear();
	con_puts(hello); 

	// jetzt wo wir schon im Kernel drin sind, wollen wir auch
	// nicht mehr raus ;)
	while (1);
	return 0;
}

