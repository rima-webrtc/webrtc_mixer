#!/bin/bash

  src=`find ./ -name "*.h" `
  echo $src
  for obj in $src
  do
      echo "cp header file $obj"
      cp --parent $obj ./src/
  done
  
