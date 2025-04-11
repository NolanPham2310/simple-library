DESCRIPTION = "Program using simple-library"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "simple-library"

inherit cmake

SRC_URI = "git://github.com/NolanPham2310/my-program.git;branch=main;protocol=https"

S = "${WORKDIR}/git"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 my-program ${D}${bindir}
}

FILES:${PN} += "${bindir}/my-program"
