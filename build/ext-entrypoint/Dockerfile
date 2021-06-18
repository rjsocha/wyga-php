FROM scratch AS base
WORKDIR /usr/bin
COPY wyga-php-ext-entrypoint .
FROM scratch 
COPY --from=base / /
ENTRYPOINT ["/usr/bin/wyga-php-ext-entrypoint"]
LABEL org.opencontainers.image.vendor="wyga"
LABEL org.opencontainers.image.url="https://github.com/rjsocha/wyga-php"
LABEL org.opencontainers.image.documentation="https://github.com/rjsocha/wyga-php/wiki"
