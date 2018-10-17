/*****************************************************************************
 * d3d11_shaders.h: Direct3D11 Shaders
 *****************************************************************************
 * Copyright (C) 2017 VLC authors and VideoLAN
 *
 * Authors: Steve Lhomme <robux4@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef VLC_D3D11_SHADERS_H
#define VLC_D3D11_SHADERS_H

#include "../../video_chroma/d3d11_fmt.h"
#include <dxgi1_4.h>

typedef enum video_color_axis {
    COLOR_AXIS_RGB,
    COLOR_AXIS_YCBCR,
} video_color_axis;

typedef struct {
    DXGI_COLOR_SPACE_TYPE   dxgi;
    const char              *name;
    video_color_axis        axis;
    video_color_primaries_t primaries;
    video_transfer_func_t   transfer;
    video_color_space_t     color;
    bool                    b_full_range;
} dxgi_color_space;

typedef struct {
    const dxgi_color_space   *colorspace;
    unsigned                 luminance_peak;
} display_info_t;

const char* globVertexShaderFlat;
const char* globVertexShaderProjection;

ID3DBlob* D3D11_CompileShader(vlc_object_t *, const d3d11_handle_t *, const d3d11_device_t *,
                              const char *psz_shader, bool pixel);
#define D3D11_CompileShader(a,b,c,d,e)  D3D11_CompileShader(VLC_OBJECT(a),b,c,d,e)

bool IsRGBShader(const d3d_format_t *);

HRESULT D3D11_CompilePixelShader(vlc_object_t *, d3d11_handle_t *, bool legacy_shader,
                                 d3d11_device_t *, const d3d_format_t *, const display_info_t *,
                                 video_transfer_func_t, bool src_full_range,
                                 ID3D11PixelShader **output);
#define D3D11_CompilePixelShader(a,b,c,d,e,f,g,h,i) \
    D3D11_CompilePixelShader(VLC_OBJECT(a),b,c,d,e,f,g,h,i)
#endif /* VLC_D3D11_SHADERS_H */
