package main

import (
	"fmt"
	"github.com/faiface/pixel"
	"github.com/faiface/pixel/pixelgl"
	"github.com/faiface/pixel/text"
	"github.com/racerxdl/wimatrix-emulator/components/ledpanel"
	"github.com/racerxdl/wimatrix-emulator/target"
	"golang.org/x/image/colornames"
	"golang.org/x/image/font/basicfont"
	"strings"
)

const maxLines = 48

var screenOrigin pixel.Matrix
var visualConsole *text.Text

var logLines []string

func removeEmpty(s []string) []string {
	var r []string
	for _, str := range s {
		if str != "" {
			r = append(r, str)
		}
	}
	return r
}

var lineBuff = ""

func stdout(line string) {
	if strings.Index(line, "\n") == -1 {
		// Buffer out
		lineBuff += line
		return
	}

	line = lineBuff + line
	lines := removeEmpty(strings.Split(line, "\n"))
	logLines = append(logLines, lines...)

	if len(logLines) > maxLines {
		logLines = logLines[len(logLines)-maxLines:]
	}
	lineBuff = ""
}

func MoveTo(x, y float64, s pixel.Picture) pixel.Matrix {
	return pixel.IM.
		Moved(pixel.V(s.Bounds().W()/2+x, s.Bounds().H()/2+y)).
		Chained(screenOrigin)
}

func ArduinoLoop() {
	for {
		target.Loop()
	}
}

func updateConsole() {
	visualConsole.Clear()
	visualConsole.Color = colornames.Black

	for _, line := range logLines {
		fmt.Fprintf(visualConsole, line+"\n")
	}
}

func run() {

	fmt.Println("Loading library")
	target.SetRedirectOut(stdout)

	//err := target.Load("./testserial.so")
	err := target.Load("./testwifi.so")
	if err != nil {
		panic(err)
	}
	target.Setup()

	go ArduinoLoop()

	cfg := pixelgl.WindowConfig{
		Title:  "Wimatrix Emulator",
		Bounds: pixel.R(0, 0, 1280, 720),
	}

	win, err := pixelgl.NewWindow(cfg)
	if err != nil {
		panic(err)
	}

	panel := ledpanel.MakePanel(30, 10)

	for x := 0; x < 30; x++ {
		for y := 0; y < 10; y++ {
			panel.SetLed(x, y, colornames.Fuchsia)
		}
	}

	panel.UpdateImage()

	atlas := text.NewAtlas(
		basicfont.Face7x13,
		text.ASCII,
	)

	visualConsole = text.New(pixel.V(0, 0), atlas)

	screenOrigin = pixel.IM.
		ScaledXY(pixel.V(0, 0), pixel.V(1, -1)).
		Moved(pixel.V(0, win.Bounds().H()))

	r := win.Bounds()
	w := r.Max.X
	h := r.Max.Y

	for !win.Closed() {
		updateConsole()

		panelPic := panel.GetPictureData()

		win.Clear(colornames.Skyblue)
		pixel.NewSprite(panelPic, panelPic.Bounds()).
			Draw(win, MoveTo(50, 50, panelPic))

		visualConsole.Draw(win, pixel.IM.Moved(pixel.V(w-500, h-25)))

		win.Update()
	}
}

func main() {
	pixelgl.Run(run)
}
