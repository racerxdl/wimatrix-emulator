package main

import (
	"github.com/faiface/pixel"
	"github.com/faiface/pixel/pixelgl"
	"github.com/racerxdl/wimatrix-emulator/components/ledpanel"
	"golang.org/x/image/colornames"
)

var screenOrigin pixel.Matrix

func MoveTo(x, y float64, s *pixel.PictureData) pixel.Matrix {
	return pixel.IM.
		Moved(pixel.V(s.Bounds().W()/2+x, s.Bounds().H()/2+y)).
		Chained(screenOrigin)
}

func run() {
	cfg := pixelgl.WindowConfig{
		Title:  "Wimatrix Emulator",
		Bounds: pixel.R(0, 0, 1280, 720),
	}

	win, err := pixelgl.NewWindow(cfg)
	if err != nil {
		panic(err)
	}

	win.Clear(colornames.Skyblue)

	panel := ledpanel.MakePanel(30, 10)

	for x := 0; x < 30; x++ {
		for y := 0; y < 10; y++ {
			panel.SetLed(x, y, colornames.Fuchsia)
		}
	}

	panel.UpdateImage()

	screenOrigin = pixel.IM.
		ScaledXY(pixel.V(0, 0), pixel.V(1, -1)).
		Moved(pixel.V(0, win.Bounds().H()))

	for !win.Closed() {
		panelPic := panel.GetPictureData()
		pixel.NewSprite(panelPic, panelPic.Bounds()).
			Draw(win, MoveTo(50, 50, panelPic))

		win.Update()
	}
}

func main() {
	pixelgl.Run(run)
}
