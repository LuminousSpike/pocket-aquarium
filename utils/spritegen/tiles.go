package main

import (
	"image"
	"image/color"
	"image/png"
	"os"
)

// BackgroundTile represents an 8x8 tile
type BackgroundTile struct {
	Pixels [8][8]color.Color
}

// NewBackgroundTile creates a new BackgroundTile from an image.Image
func NewBackgroundTile(img image.Image, startX, startY int) BackgroundTile {
	tile := BackgroundTile{}
	for y := 0; y < 8; y++ {
		for x := 0; x < 8; x++ {
			tile.Pixels[y][x] = img.At(startX+x, startY+y)
		}
	}
	return tile
}

// colorToGameBoy converts a color.Color to a Game Boy color (0-3)
func colorToGameBoy(c color.Color) byte {
	r, g, b, a := c.RGBA()

	if a == 0 {
		return 1 // White
	}

	gray := (r + g + b) / 3
	switch {
	case gray < 0x4000:
		return 3 // Black
	case gray < 0x8000:
		return 2 // Dark Gray
	case gray < 0xC000:
		return 1 // Light Gray
	default:
		return 0 // White
	}
}

// Encode converts the BackgroundTile to the Game Boy's tile format
func (t *BackgroundTile) Encode() []byte {
	encoded := make([]byte, 16)
	for y := 0; y < 8; y++ {
		var lowByte, highByte byte

		for x := 0; x < 8; x++ {
			color := colorToGameBoy(t.Pixels[y][x])

			lowByte |= (color & 1) << (7 - x)
			highByte |= ((color >> 1) & 1) << (7 - x)
		}

		encoded[y*2] = lowByte
		encoded[y*2+1] = highByte
	}
	return encoded
}

// Save to png
func (t *BackgroundTile) SavePNG(outPath string) error {
	img := image.NewRGBA(image.Rect(0, 0, 8, 8))
	for y := 0; y < 8; y++ {
		for x := 0; x < 8; x++ {
			img.Set(x, y, t.Pixels[y][x])
		}
	}

	fh, err := os.Create(outPath)
	if err != nil {
		return err
	}
	defer fh.Close()

	return png.Encode(fh, img)
}

// Ecnode to GameBoy format
func (t *BackgroundTile) EncodeGB() []byte {
	encoded := make([]byte, 16)

	for y := 0; y < 8; y++ {
		var lowByte, highByte byte
		for x := 0; x < 8; x++ {
			color := colorToGameBoy(t.Pixels[y][x])
			lowByte |= (color & 1) << (7 - x)
			highByte |= ((color >> 1) & 1) << (7 - x)
		}
		encoded[y*2] = lowByte
		encoded[y*2+1] = highByte
	}

	return encoded
}
