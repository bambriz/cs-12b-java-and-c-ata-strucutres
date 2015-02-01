JAVASRC   = jfmt.java
SOURCES   = README Makefile ${JAVASRC}
MAINCLASS = jfmt
CLASSES   = jfmt.class
JARFILE   = jfmt
JARCLASSES= ${CLASSES}
SUBMITDIR = cmps012b-wm.f13 asg1

all: ${JARFILE}

${JARFILE}: ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${{JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class: %.java
	cid + $<
	javac $<

clean:
	- rm ${CLASSES} test.output

spotless: clean
	-rm ${JARFILE}
	-ls -ago

ci: ${SOURCES}
	cid + ${SOURCES}

check: ${SOURCES}
	- checksource ${SOURCES}

test: ${JARFILE}
	( echo "%%%%%%%% ${JARFILE}" \
	; ${JARFILE} 2>&1 \
	; echo "%%%%%%%% Exit status = $$?" \
	; echo "%%%%%%%% uname -a" ; uname -a | sed 's/#/\n#/'\
	) >test.output
	cat -nv test.output

submit: check ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}

again:
	 gmake --no-print-directory spotless ci all test check
                                                             
