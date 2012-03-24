all: mapnik

install:
	python scons/scons.py install

mapnik:
	python scons/scons.py

clean:
	python scons/scons.py -c

reset:
	if test -e ".sconf_temp/"; then rm -r ".sconf_temp/"; fi
	if test -e ".sconsign.dblite"; then rm ".sconsign.dblite"; fi
	if test -e "config.cache"; then rm "config.cache"; fi

uninstall:
	python scons/scons.py uninstall

test:
	@python tests/visual_tests/test.py
	@tests/cpp_tests/font_registration_test
	@tests/cpp_tests/params_test
	@python tests/run_tests.py -q

pep8:
	# https://gist.github.com/1903033
	# gsed on osx
	@pep8 -r --select=W293 -q --filename=*.py `pwd`/tests/ | xargs gsed -i 's/^[ \r\t]*$//'
	@pep8 -r --select=W391 -q --filename=*.py `pwd`/tests/ | xargs gsed -i -e :a -e '/^\n*$/{$d;N;ba' -e '}'

grind:
	@valgrind --leak-check=full tests/cpp_tests/font_registration_test

.PHONY: clean reset uninstall test install
