<?php
if(!extension_loaded('mysqli')) {
	echo "missing ext mysqli\n";
	exit(1);
}
if(!extension_loaded('pdo_mysql')) {
	echo "missing ext pdo_mysql\n";
	exit(1);
}
if(!extension_loaded('v8js')) {
	echo "missing ext v8js\n";
	exit(1);
}
var_dump(get_loaded_extensions());
exit(0);
