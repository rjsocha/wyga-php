<?php
chdir("/check");
/* Read the image */
$im = new Imagick("test.png");

/* Thumbnail the image */
$im->thumbnailImage(200, null);

/* Create a border for the image */
$im->borderImage(new ImagickPixel("white"), 5, 5);

/* Clone the image and flip it */
$reflection = $im->clone();
$reflection->flipImage();

/* Create gradient. It will be overlayed on the reflection */
$gradient = new Imagick();

/* Gradient needs to be large enough for the image and the borders */
$gradient->newPseudoImage($reflection->getImageWidth() + 10, $reflection->getImageHeight() + 10, "gradient:transparent-black");

/* Composite the gradient on the reflection */
$reflection->compositeImage($gradient, imagick::COMPOSITE_OVER, 0, 0);

/* Add some opacity. Requires ImageMagick 6.2.9 or later */
$reflection->setImageOpacity( 0.3 );
print_r($im);
echo "OK\n";
exit(0);
