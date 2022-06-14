all:
	./build base
	./build base-fpm
	./build base-cli
	./build base-merge
	./build ext
	./build ext:igbinary
	./build ext:gmagick
	./build ext:luasandbox
	./build package
	./build package:igbinary
	./build package:gmagick
	./build package:luasandbox
publish:
	./build publish

md:
	./build md
