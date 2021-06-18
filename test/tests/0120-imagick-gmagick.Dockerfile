ARG V
FROM wyga/php-ext-gmagick:${V}
FROM wyga/php-ext-imagick:${V}
FROM wyga/merge:2 AS merge
ARG V
FROM wyga/php-merge:$V
COPY / /check/
