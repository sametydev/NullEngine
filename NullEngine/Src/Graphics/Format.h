#pragma once

enum DXGI_FORMAT;


namespace format {
	DXGI_FORMAT FormatToDX(uint count, Format format);
	GLenum		FormatToGL(Format format);
	GLenum		TopologyToGL(Topolgy topolgy);
}


