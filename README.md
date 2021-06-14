PoC wyga PHP modular system (binary distribution)

By example:

Standard build:

```
FROM php:7.4.20-fpm-buster
ADD https://github.com/mlocati/docker-php-extension-installer/releases/latest/download/install-php-extensions /usr/local/bin/
RUN chmod +x /usr/local/bin/install-php-extensions && sync && \
  install-php-extensions \
        igbinary \
        yaml \
        imagick \
        exif \
        pdo_mysql \
        mysqli \
        gd \
        mcrypt \
        intl 
```
