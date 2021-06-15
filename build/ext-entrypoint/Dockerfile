FROM scratch AS base
WORKDIR /usr/bin
COPY wyga-php-ext-entrypoint .
FROM scratch 
COPY --from=base / /
ENTRYPOINT ["/usr/bin/wyga-php-ext-entrypoint"]
