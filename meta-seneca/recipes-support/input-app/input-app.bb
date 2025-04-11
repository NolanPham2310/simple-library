DESCRIPTION = "Input App"
LICENSE = "CLOSED"
SRC_URI = "file://input_app.c"
S = "${WORKDIR}"
do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/input_app.c -o input_app
}
do_install() {
    install -d ${D}${bindir}
    install -m 0755 input_app ${D}${bindir}
}
