
This is a feature reduced version of pmake-1.111.tar.gz from (1), (2) or
(3) with the intent of validating simple makefiles.

Please note that even some posix features were removed, like archive
library handling.  There is one additional feature though: a target name
with a ".stamp" suffix can be used to check for out-of-date/up-to-date
state if it is a prerequisite of a .STAMP special target, this is just a
backwards compatible optimization for workflows that derive many targets
from a single source, like noweb.

- (1): http://ftp.fau.de/gentoo/distfiles/pmake_1.111.orig.tar.gz
- (2): http://archive.debian.org/debian/pool/main/p/pmake/pmake_1.111.orig.tar.gz
- (3): https://mirrors.slackware.com/slackware/slackware-14.2/source/d/pmake/pmake-1.111.tar.gz

All three files above are the same, with SHA256 of
dde37ac618f19a7cce174754c207e90501cab362b51f904bcfb20dfb24a13539.

All licenses, all BSD, are included in individual files.

To build simply run ./test.sh on a linux with gcc, customizing the build for
other systems should be trivial.

--ctarbide
