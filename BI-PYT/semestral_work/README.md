# Graphic Editor

Graphic Editor is a Python application for editing and enhancing photos straight from the command line.

## Installation

Only requirement to run the app is Python, you don't need to install anything.

## Available options
| Option            | Effect                                                        |
| ----------------- | ------------------------------------------------------------- |
| --help            | `Lists all the available options in case you forget.`         |
| --rotate          | `Rotates given image by 90 degrees to the right.`             |
| --mirror          | `Mirrors the given image.`                                    |
| --inverse         | `Inverts the colours of the given image.`                     |
| --bw              | `Transforms the given image into black and white/grayscale.`  |
| --lighten <0-100> | `Lightens the given image by a percentage of your choice.`    |
| --darken <0-100>  | `Darkens the given image by a percentage of your choice.`     |
| --sharpen         | `Sharpens the given image.`                                   |

## Usage

You can apply as many options as you want, the minimum is one. The effects will be applied
one by one, from first to last (meaning that the effects will pile on each other).

Make sure you're in the 'filtering' folder.

Then just simply run the application:
```bash
python graphic_editor OPTIONS INPUT_IMAGE_PATH OUTPUT_IMAGE_PATH
```

Example (Image will be rotated, transformed into black and white and, lightened by 25% and saved in the same directory with a new filename):
```bash
python graphic_editor --rotate --bw --lighten 25 lenna.png lenna_edit.png
```
