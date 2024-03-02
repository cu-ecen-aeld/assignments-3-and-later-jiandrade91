#!/bin/bash
# Script outline to install and build kernel.
# Author: Siddhant Jajoo.

set -e
set -u

OUTDIR=/tmp/aeld
KERNEL_REPO=git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
KERNEL_VERSION=v5.1.10
BUSYBOX_VERSION=1_33_1
FINDER_APP_DIR=$(realpath $(dirname $0))
ARCH=arm64
CROSS_COMPILE=aarch64-none-linux-gnu-

if [ $# -lt 1 ]
then
	echo "Using default directory ${OUTDIR} for output"
else
	OUTDIR=$1
	echo "Using passed directory ${OUTDIR} for output"
fi

mkdir -p ${OUTDIR}

cd "$OUTDIR"
if [ ! -d "${OUTDIR}/linux-stable" ]; then
    #Clone only if the repository does not exist.
	echo "CLONING GIT LINUX STABLE VERSION ${KERNEL_VERSION} IN ${OUTDIR}"
	git clone ${KERNEL_REPO} --depth 1 --single-branch --branch ${KERNEL_VERSION}
fi
if [ ! -e ${OUTDIR}/linux-stable/arch/${ARCH}/boot/Image ]; then
    cd linux-stable
    echo "Checking out version ${KERNEL_VERSION}"
    git checkout ${KERNEL_VERSION}

    # TODO: Add your kernel build steps here
<<<<<<< HEAD
<<<<<<< HEAD
    make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- mrproper
    make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- defconfig
    make -j8 ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- all
    make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- modules
    make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- dtbs
=======
>>>>>>> assignments-base/assignment4
||||||| c93ab2a
=======
    make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- mrproper # Clean the kernel build tree
    make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- defconfig # For the "vir" arm dev board
    make -j8 ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- all # build a kernel image for booting QEMU
    make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- modules # build any kernel modules
    make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- dtbs # build the devicetree
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab
fi

echo "Adding the Image in outdir" # To linux-stable/arch/arm64/boot/Image??
cp ${OUTDIR}/linux-stable/arch/${ARCH}/boot/Image ${OUTDIR}/

echo "Creating the staging directory for the root filesystem"
cd "$OUTDIR"
if [ -d "${OUTDIR}/rootfs" ]
then
	echo "Deleting rootfs directory at ${OUTDIR}/rootfs and starting over"
    sudo rm  -rf ${OUTDIR}/rootfs
fi

# TODO: Create necessary base directories
mkdir -p rootfs
cd rootfs
mkdir -p bin dev etc home lib lib64 proc sbin sys tmp usr var 
mkdir -p usr/bin usr/lib usr/sbin 
mkdir -p  var/log 

<<<<<<< HEAD
mkdir -p rootfs
cd rootfs
mkdir -p bin dev etc home lib lib64 proc sys tmp usr var
mkdir -p usr/bin usr/lib usr/sbin
mkdir -p var/log

=======
>>>>>>> assignments-base/assignment4
cd "$OUTDIR"
if [ ! -d "${OUTDIR}/busybox" ]
then
git clone git://busybox.net/busybox.git
    cd busybox
    git checkout ${BUSYBOX_VERSION}
    # TODO:  Configure busybox
<<<<<<< HEAD
<<<<<<< HEAD
    make distclean
    make defconfig
=======
>>>>>>> assignments-base/assignment4
||||||| c93ab2a
=======
    make distclean
    make defconfig
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab
else
    cd busybox
fi

# TODO: Make and install busybox
<<<<<<< HEAD
<<<<<<< HEAD
make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} distclean
make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} defconfig
make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE}
make CONFIG_PREFIX="$OUTDIR"/rootfs ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} install
cd "${OUTDIR}/rootfs"

=======
>>>>>>> assignments-base/assignment4
||||||| c93ab2a
=======
make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} distclean
make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} defconfig
make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE}
make CONFIG_PREFIX="$OUTDIR"/rootfs ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} install
cd "${OUTDIR}/rootfs"
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab

echo "Library dependencies"
# Need to change directories back to OUTDIR/rootfs
${CROSS_COMPILE}readelf -a bin/busybox | grep "program interpreter"
${CROSS_COMPILE}readelf -a bin/busybox | grep "Shared library"

<<<<<<< HEAD
# TODO: Add library dependencies to rootfs

<<<<<<< HEAD
export SYSROOT=$(${CROSS_COMPILE}gcc -print-sysroot)

sudo cp -r $SYSROOT/lib/* ${OUTDIR}/rootfs/lib
sudo cp -r $SYSROOT/lib/ld-linux-aarch64.so.1 ${OUTDIR}/rootfs/lib
sudo cp -r $SYSROOT/lib64/* ${OUTDIR}/rootfs/lib64
sudo cp -r $SYSROOT/lib64/libm.so.6 ${OUTDIR}/rootfs/lib64
sudo cp -r $SYSROOT/lib64/libresolv.so.2 ${OUTDIR}/rootfs/lib64
sudo cp -r $SYSROOT/lib64/libc.so.6 ${OUTDIR}/rootfs/lib64

# TODO: Make device nodes

sudo mknod -m 666 dev/null c 1 3
sudo mknod -m 622 dev/console c 5 1

# TODO: Clean and build the writer utility
cd "$FINDER_APP_DIR"
make clean
make CROSS_COMPILE=$CROSS_COMPILE

=======
||||||| c93ab2a
# TODO: Add library dependencies to rootfs

=======
# TODO: Add library dependencies to rootfs. Copy them over from sysroot
export SYSROOT=$(${CROSS_COMPILE}gcc -print-sysroot)
sudo cp -r $SYSROOT/lib64/* "${OUTDIR}/rootfs/lib64"
sudo cp -r $SYSROOT/lib/* "${OUTDIR}/rootfs/lib"
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab
# TODO: Make device nodes
# cd "${OUTDIR}"/rootfs
sudo mknod -m 666 dev/null c 1 3
sudo mknod -m 666 dev/console c 5 1 

<<<<<<< HEAD
# TODO: Clean and build the writer utility
>>>>>>> assignments-base/assignment4
||||||| c93ab2a
# TODO: Clean and build the writer utility
=======
# TODO: Clean and build the writer utility in finder-app
cd "$FINDER_APP_DIR"
make clean
make CROSS_COMPILE=$CROSS_COMPILE
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab

# TODO: Copy the finder related scripts and executables to the /home directory
# on the target rootfs
mkdir "$OUTDIR"/rootfs/home/conf
cp finder.sh finder-test.sh writer autorun-qemu.sh "$OUTDIR"/rootfs/home
cp conf/assignment.txt "$OUTDIR"/rootfs/home/conf
cp conf/username.txt "$OUTDIR"/rootfs/home/conf

<<<<<<< HEAD
mkdir -p ${OUTDIR}/rootfs/home/conf
cp autorun-qemu.sh finder.sh finder-test.sh writer ${OUTDIR}/rootfs/home
cp ${FINDER_APP_DIR}/conf/username.txt ${OUTDIR}/rootfs/home/conf
cp ${FINDER_APP_DIR}/conf/assignment.txt ${OUTDIR}/rootfs/home/conf

# TODO: Chown the root directory

cd ${OUTDIR}/rootfs
sudo chown -R root:root *

# TODO: Create initramfs.cpio.gz

find . | cpio -H newc -ov --owner root:root > ${OUTDIR}/initramfs.cpio
cd ${OUTDIR}
gzip -f ${OUTDIR}/initramfs.cpio

=======
# TODO: Chown the root directory
cd "$OUTDIR"/rootfs
sudo chown -R root:root *

# TODO: Create initramfs.cpio.gz
<<<<<<< HEAD
>>>>>>> assignments-base/assignment4
||||||| c93ab2a
=======
find . | cpio -H newc -ov --owner root:root > "$OUTDIR"/initramfs.cpio
cd "$OUTDIR"
gzip -f "$OUTDIR"/initramfs.cpio
>>>>>>> fba2e58ad3d21857af7a1ed8df42a287a6ea3dab
