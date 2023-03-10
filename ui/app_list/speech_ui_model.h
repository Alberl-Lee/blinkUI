// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_SPEECH_UI_MODEL_H_
#define UI_APP_LIST_SPEECH_UI_MODEL_H_

#include <stdint.h>

#include "base/macros.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "ui/app_list/app_list_export.h"
#include "ui/app_list/speech_ui_model_observer.h"
#include "ui/gfx/image/image_skia.h"

namespace app_list {

// SpeechUIModel provides the interface to update the UI for speech recognition.
class APP_LIST_EXPORT SpeechUIModel {
public:
    // Construct the model, initially in state SPEECH_RECOGNITION_OFF.
    SpeechUIModel();
    virtual ~SpeechUIModel();

    void SetSpeechResult(const base::string16& result, bool is_final);
    void UpdateSoundLevel(int16_t level);
    // Sets the speech recognition state. If |always_show_ui| is true,
    // sends the state change to the UI observers regardless of whether
    // the |new_state| is different from the old one.
    void SetSpeechRecognitionState(SpeechRecognitionState new_state,
        bool always_show_ui);

    void AddObserver(SpeechUIModelObserver* observer);
    void RemoveObserver(SpeechUIModelObserver* observer);

    const base::string16& result() const { return result_; }
    bool is_final() const { return is_final_; }
    int16_t sound_level() const { return sound_level_; }
    SpeechRecognitionState state() const { return state_; }
    const gfx::ImageSkia& logo() const { return logo_; }
    void set_logo(const gfx::ImageSkia& logo) { logo_ = logo; }

private:
    base::string16 result_;
    bool is_final_;
    int16_t sound_level_;
    SpeechRecognitionState state_;

    // The logo image which the speech UI will show at the top-left.
    gfx::ImageSkia logo_;

    // The sound level range to compute visible sound-level.
    int16_t minimum_sound_level_;
    int16_t maximum_sound_level_;

    base::ObserverList<SpeechUIModelObserver> observers_;

    DISALLOW_COPY_AND_ASSIGN(SpeechUIModel);
};

} // namespace app_list

#endif // UI_APP_LIST_SPEECH_UI_MODEL_H_
