wget http://apt-cyg.googlecode.com/svn/trunk/apt-cyg
chmod a+x apt-cyg
mv apt-cyg /usr/local/bin
apt-cyg install aspell aspell-dev bc bison bzip2 gcc gcc4    \
    gettext-devel gzip jpeg libpng libtool m4 make           \
    patch pkg-config python sed tar util-linux

cd qtwin-4.7.4/build-cygwin

../configure -prefix /usr/local/qt/4.7.4 -platform cygwin-g++-win32            \
    -release -static -fast -qt-sql-sqlite -no-reduce-exports -no-qt3support    \
    -no-exceptions -no-largefile -no-rpath -no-nis -no-cups -no-pch -no-opengl \
    -no-glib -no-gstreamer -no-phonon -no-webkit

make sub-tools-bootstrap sub-moc sub-rcc sub-uic sub-corelib sub-gui

make sub-moc-install_subtargets sub-rcc-install_subtargets     \
     sub-uic-install_subtargets sub-corelib-install_subtargets \
     sub-gui-install_subtargets

ln -s moc.exe /usr/local/qt/4.7.4/bin/moc-qt4
ln -s uic.exe /usr/local/qt/4.7.4/bin/uic-qt4

cd ../..
./lyxconfig-cygwin lyx

cd lyx/build-cygwin
make
make install
