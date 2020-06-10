package ledpanel

import (
	"github.com/faiface/pixel"
	"golang.org/x/image/colornames"
	"image"
	"image/color"
)

const (
	ledSize     = 12          // Pixels
	ledSpace    = ledSize / 2 // Pixels
	panelMargin = 16          // Pixels
)

type Panel struct {
	width, height int
	leds          []color.Color
	pic           *pixel.PictureData
}

func MakePanel(width, height int) *Panel {
	return &Panel{
		width:  width,
		height: height,
		leds:   make([]color.Color, width*height),
	}
}

func (p *Panel) SetLed(x, y int, c color.Color) {
	point := y*p.width + x

	if len(p.leds) > point {
		p.leds[point] = c
	}
}

func (p *Panel) SetLeds(leds []color.Color) {
	copy(p.leds, leds)
}

func (p *Panel) SetPixel(x, y int, c color.RGBA) {
	idx := p.pic.Index(pixel.V(float64(x), float64(y)))
	p.pic.Pix[idx] = c
}

func (p *Panel) SetLedIdx(idx int, c color.RGBA) {
	p.leds[idx] = c
}

func (p *Panel) drawLed(ox, oy int, c color.Color) {
	r, g, b, a := c.RGBA()

	rgbac := color.RGBA{
		R: uint8(r),
		G: uint8(g),
		B: uint8(b),
		A: uint8(a),
	}

	for x := ox; x < ox+ledSize; x++ {
		for y := oy; y < oy+ledSize; y++ {
			p.SetPixel(x, y, rgbac)
		}
	}
}

func (p *Panel) UpdateImage() {
	if p.pic == nil {
		imgWidth := panelMargin*2 + p.width*(ledSize+ledSpace) - ledSpace
		imgHeight := panelMargin*2 + p.height*(ledSize+ledSpace) - ledSpace
		p.pic = pixel.PictureDataFromImage(image.NewRGBA(image.Rect(0, 0, imgWidth, imgHeight)))
	}

	for i := 0; i < len(p.pic.Pix); i++ {
		p.pic.Pix[i] = colornames.Black
	}

	for ledx := 0; ledx < p.width; ledx++ {
		for ledy := 0; ledy < p.height; ledy++ {
			ledColor := p.leds[ledy*p.width+ledx]
			ox := panelMargin + ledx*(ledSize+ledSpace)
			oy := panelMargin + ledy*(ledSize+ledSpace)
			p.drawLed(ox, oy, ledColor)
		}
	}
}

func (p *Panel) GetPictureData() *pixel.PictureData {
	return p.pic
}
