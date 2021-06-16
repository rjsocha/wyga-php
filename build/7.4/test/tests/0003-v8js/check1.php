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
echo "V8JS OK\n";

$v8 = new V8Js();

/* basic.js */
$JS = <<< EOT
len = print('Hello' + ' ' + 'World!' + "\\n");
len;
EOT;

try {
	  var_dump($v8->executeString($JS, 'basic.js'));
} catch (V8JsException $e) {
	var_dump($e);
	exit(1);
}

$JS = <<< EOT
x=4+90;
EOT;
$n=$v8->executeString($JS, 'basic.js');
echo "RES: $n\n";
var_dump($n);
if($n==94) exit (0);
exit(1);
