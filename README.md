### stupiddns - A special purpose DNS server

## Pre build instructions


#Dependencies
Sorry bu you'll need an installation of a libevent with at least a version of 2.0.0 .
Actually I've tested just version 2.0.7 yet... (and it works for me :)


# Get the source code
You already have it, don't you? Otherwise encurage me to fix the instructions
here and follow them afterwards


## Build from source arcive:
To build this stupiddns server you are equipped with the usual auto hell stuff

# example instructions (you may have to adapt  by use of brains....)

	autoreconf -si
	./configure
	make
	make install

You may of course do all the stuff that influences the configuration, like give the --prefix at the configure line or set the environment for cross-compiling this stuff. 
./configure --help along with the INSTALL file in the source dir could provide you with some pointers on that.



# alternate instrunctions (avoiding autohell. May need more brains --deprecated )
	
	$EDITOR Makefile.bak (and fix libeventpath....)
	make -f Makefile.bak
	ln -s stupiddns /usr/local/bin

## Package for <insertyourbinarydistributionhere>

Please provide them yourself and contribute back

##License
shall be noted in COPYING otherwise the GPL v2 applies with the explicit addition that 
donations in form of "Club Mate" or beer are welcome. Think of buy a whole bunch of beer
and donate bottles of it to several open source projects you use, since most 
FLOSS-programers will fight a better battle on the field of software development for you,
when they are cheered up from time to time.

