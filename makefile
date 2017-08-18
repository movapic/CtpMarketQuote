all :
	cd source && make all
	mv source/tickquote build/bin/
	cp source/*.json build/bin/
	cd tool && make all
	mv tool/tickfetch build/bin/

clean :
	rm -f build/bin/*
