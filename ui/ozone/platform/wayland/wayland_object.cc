// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/ozone/platform/wayland/wayland_object.h"

#include <wayland-client.h>
#include <xdg-shell-unstable-v5-client-protocol.h>

namespace wl {

const wl_interface* ObjectTraits<wl_buffer>::interface = &wl_buffer_interface;
void (*ObjectTraits<wl_buffer>::deleter)(wl_buffer*) = &wl_buffer_destroy;

const wl_interface* ObjectTraits<wl_compositor>::interface = &wl_compositor_interface;
void (*ObjectTraits<wl_compositor>::deleter)(wl_compositor*) = &wl_compositor_destroy;

const wl_interface* ObjectTraits<wl_display>::interface = &wl_display_interface;
void (*ObjectTraits<wl_display>::deleter)(wl_display*) = &wl_display_disconnect;

const wl_interface* ObjectTraits<wl_registry>::interface = &wl_registry_interface;
void (*ObjectTraits<wl_registry>::deleter)(wl_registry*) = &wl_registry_destroy;

const wl_interface* ObjectTraits<wl_shm>::interface = &wl_shm_interface;
void (*ObjectTraits<wl_shm>::deleter)(wl_shm*) = &wl_shm_destroy;

const wl_interface* ObjectTraits<wl_shm_pool>::interface = &wl_shm_pool_interface;
void (*ObjectTraits<wl_shm_pool>::deleter)(wl_shm_pool*) = &wl_shm_pool_destroy;

const wl_interface* ObjectTraits<wl_surface>::interface = &wl_surface_interface;
void (*ObjectTraits<wl_surface>::deleter)(wl_surface*) = &wl_surface_destroy;

const wl_interface* ObjectTraits<xdg_shell>::interface = &xdg_shell_interface;
void (*ObjectTraits<xdg_shell>::deleter)(xdg_shell*) = &xdg_shell_destroy;

const wl_interface* ObjectTraits<xdg_surface>::interface = &xdg_surface_interface;
void (*ObjectTraits<xdg_surface>::deleter)(xdg_surface*) = &xdg_surface_destroy;

} // namespace wl
