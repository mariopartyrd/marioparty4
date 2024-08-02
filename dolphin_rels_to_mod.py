import os
import shutil
import sys

"""
Usage: extract an mp4 iso to mod_root/orig/
Build the dtk project, then run this script which you can then run your mod changes by running
mod_root/mod/sys/main.dol in dolphin
"""

def copy_build_files_to_mod(src_dir, dest_dir):
    #copy dol
    build_dol = "build/GMPE01_00/main.dol"
    mod_dol_dir = "mod_root/mod/sys/main.dol"
    shutil.copy(build_dol, mod_dol_dir)
    print(f"Copied {build_dol} to {mod_dol_dir}")

    #copy rels
    rel_files_found = False
    for root, dirs, files in os.walk(src_dir):
        for file in files:
            if file.endswith('.rel'):
                rel_files_found = True
                source_path = os.path.join(root, file)
                destination_path = os.path.join(dest_dir, file)

                # Create destination directory if it doesn't exist
                os.makedirs(os.path.dirname(destination_path), exist_ok=True)

                # Copy .rel file to root/dll/
                shutil.copy(source_path, destination_path)

                print(f"{file} found and copied to {destination_path}")

    if not rel_files_found:
        print("No .rel files found.")

def copy_mod_orig_to_mod(mod_orig, mod_dir):
    # Ensure the mod directory exists
    os.makedirs(mod_dir, exist_ok=True)
    
    # Iterate through all items in the source directory
    for item in os.listdir(mod_orig):
        s = os.path.join(mod_orig, item)
        d = os.path.join(mod_dir, item)
        # If the item is a directory, copy it to the destination
        if os.path.isdir(s):
            shutil.copytree(s, d, dirs_exist_ok=True)
            print(f"Copied directory {s} to {d}")

def main():
    src_directory = "build/GMPE01_00"
    rels_destination_directory = "mod_root/mod/files/dll"
    mod_dest = "mod_root/"
    mod_orig = "mod_root/orig/"
    mod_dir = "mod_root/mod/"

    if not os.path.isdir(mod_dest):
        raise FileNotFoundError(f"The directory {mod_dest} does not exist. Manually create a mod_root/ directory at the root of the project.")
    if not os.path.isdir(mod_orig):
        raise FileNotFoundError(f"The directory {mod_orig} does not exist. Extract the entire iso to mod_root/orig/")

    if '--clean' in sys.argv:
        print("--clean option detected. Copying directories from mod_root/orig/ to mod_root/mod/.")
        copy_mod_orig_to_mod(mod_orig, mod_dir)
    elif not os.path.isdir(mod_dir):
        os.makedirs(mod_dir)
        print(f"{mod_dir} created.")
        copy_mod_orig_to_mod(mod_orig, mod_dir)

    copy_build_files_to_mod(src_directory, rels_destination_directory)

if __name__ == "__main__":
    main()
