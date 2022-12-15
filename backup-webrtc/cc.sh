#!/bin/bash

  src=`find ./ -name "*.cc" `
  echo $src
  for obj in $src
  do
      echo "cp header file $obj"
      cp  $obj ./src/
  done
  
    src=`find ./ -name "*.c" `
  echo $src
  for obj in $src
  do
      echo "cp header file $obj"
      cp  $obj ./src/
  done
