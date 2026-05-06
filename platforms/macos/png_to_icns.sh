#!/usr/bin/env bash

# PNG to ICNS v1.0 - https://github.com/BenSouchet/png-to-icns
# Copyright(C) 2022 Ben Souchet | MIT License

usageFunction()
{
   echo "PNG to ICNS v1.0 - Easily convert your image to Mac OS icon!"
   echo ""
   echo "Usage: $0 -i <path of the .png image>"
   echo -e "\t-i Relative path of the image (.png)"
   echo -e "\t-h Display this usage message"

   # Exit / Stop the script
   exit 1
}

# If no option were passed display usage and exit
if [[ $1 == "" ]]
then
    usageFunction
fi

# Iterate over script options
while getopts "hi:" opt; do
   case "$opt" in
      i ) image_path="$OPTARG" ;;
      h | *) usageFunction ;;
   esac
done

# if empty image_path, display error message and usage
if [ -z "$image_path" ]
then
   echo "ERROR: '-i' parameter cannot be empty."
   usageFunction
fi

# if extension not .png, display error message
if [[ ! $image_path =~ .png$ ]]
then
    echo "ERROR: image path need to end with .png"
    exit 1
fi

# if image path file doesn't exists, display error message
if [ ! -f "$image_path" ]
then
    echo "ERROR: image path doesn't seems to exists on your disk."
    exit 1
fi

icon_orginal_name="icon"
icon_name=$icon_orginal_name
icon_extension="icns"

# If dest path exists, add suffix number
# to avoid the new icon file to replace an existing file
icon_index=2
while [ -f "${icon_name}.${icon_extension}" ]
do
   icon_name="${icon_orginal_name}_${icon_index}"
   icon_index=$((icon_index + 1))
done

output_iconset_name="${icon_name}.iconset"

# Create the temp directory to save the icon sizes
mkdir $output_iconset_name

# Create the icon sizes
sips -z 16 16     -s format png "$image_path" --out "${output_iconset_name}/icon_16x16.png" > /dev/null
sips -z 32 32     -s format png "$image_path" --out "${output_iconset_name}/icon_16x16@2x.png" > /dev/null
sips -z 32 32     -s format png "$image_path" --out "${output_iconset_name}/icon_32x32.png" > /dev/null
sips -z 64 64     -s format png "$image_path" --out "${output_iconset_name}/icon_32x32@2x.png" > /dev/null
sips -z 128 128   -s format png "$image_path" --out "${output_iconset_name}/icon_128x128.png" > /dev/null
sips -z 256 256   -s format png "$image_path" --out "${output_iconset_name}/icon_128x128@2x.png" > /dev/null
sips -z 256 256   -s format png "$image_path" --out "${output_iconset_name}/icon_256x256.png" > /dev/null
sips -z 512 512   -s format png "$image_path" --out "${output_iconset_name}/icon_256x256@2x.png" > /dev/null
sips -z 512 512   -s format png "$image_path" --out "${output_iconset_name}/icon_512x512.png" > /dev/null
sips -z 1024 1024 -s format png "$image_path" --out "${output_iconset_name}/icon_512x512@2x.png" > /dev/null

# Create the iconset
iconutil -c icns $output_iconset_name

# Delete the temp folder
rm -R $output_iconset_name

# Echo result status
icon_path="${icon_name}.${icon_extension}"
if [ -f "$icon_path" ]
then
    echo "INFO: The icon has been successfully created: ./${icon_path}"
else
    # First print an empty line, to help lisibility
    echo ""
    echo "ERROR: An error occurred please check the logs above."
fi

exit 0
