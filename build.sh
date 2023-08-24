#!/bin/bash
CWD=$(pwd)

apt-get install uuid-dev -y

install_submodules_manually() {
    CONTENTS=$(cat .gitmodules | grep -E '(path|url).*' | cut -d " " -f 3)
    CWD=$(pwd)

    LAST=""
    for item in ${CONTENTS[@]};
    do
    cd $CWD
    STRINGHEAD=$( echo "$item" | cut -d '/' -f 1)
        if [[ "$STRINGHEAD" == "vendor" ]]
        then
            if [[ -d "$CWD/$item" ]]
            then
                LAST=$(echo "$item")
                echo "$item already exists."
                continue
            fi
            mkdir -p "$item"
            cd $item
            LAST=$(echo "$item")
        else
            if [[ -d "$CWD/$LAST/.git" ]]
            then
                echo "$LAST already installed."
                continue
            fi
            cd "$CWD/$LAST"
            echo "Installing $item"
            git init .
            git remote add origin $item
            res=$(git pull origin master 2>&1)
            if [[ "$res" == "fatal: couldn't find remote ref master" ]]
            then
                git pull origin main
            fi
        fi
    done
}

install_modules () {
    CWD=$(pwd)
    if [[ ! -d "$CWD/vendor" ]]
    then
        mkdir $CWD/vendor
        git submodule init
        git submodule update
    fi
    if [[ ! -d "$CWD/vendor/microsoft" ]]
    then
        echo "Unable to auto-install using GIT, trying another route."
        install_submodules_manually
    else
        echo "Submodules installed."
    fi
}

if [[ ! -d "$CWD/Cardinal" ]]
then
    echo "This container must be ran within a Cardinal Context."
    exit 1
fi

install_modules

if [[ ! -f "$CWD/vendor/microsoft/GSL/build/Makefile" ]]
then
    cd $CWD/vendor/microsoft/GSL/
    mkdir build
    cd build
    cmake ..
    make
    make install
    cd $CWD
fi
if [[ ! -f "$CWD/vendor/sewenew/redis-plus-plus/build/Makefile" ]]
then
    mkdir $CWD/vendor/sewenew/redis-plus-plus/build
    cd $CWD/vendor/sewenew/redis-plus-plus/build
    cmake ..
    make
    cd $CWD
fi

if [[ ! -f "$CWD/vendor/mariusbancila/stduuid/build/Makefile" ]]
then
    mkdir $CWD/vendor/mariusbancila/stduuid/build
    cd $CWD/vendor/mariusbancila/stduuid/build
    cmake ..
    make
    cd $CWD
fi

echo "redis-plus-plus"
cd $CWD/vendor/sewenew/redis-plus-plus/build && make install
echo "GSL"
cd $CWD/vendor/microsoft/GSL/build && make install
echo "stduuid"
cd $CWD/vendor/mariusbancila/stduuid/build && make install

cd $CWD

if [[ -d "$CWD/build/" ]]
then
    rm -rf $CWD/build/*
else
    mkdir $CWD/build
fi

cd $CWD/build && cmake .. -DUSE_LIBUUID=ON && make

if [[ ! -f "$CWD/build/bin/libredis++.so.1" ]]
then
    cp $CWD/vendor/sewenew/redis-plus-plus/build/libredis++.so.1.3.6 $CWD/build/bin/libredis++.so.1
fi

if [[ ! -f "$CWD/build/bin/libcardinal.so" ]]
then
    cp "$CWD/build/lib/libcardinal.so" "$CWD/build/bin/libcardinal.so"
fi