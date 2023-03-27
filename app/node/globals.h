/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2022 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef NODEGLOBALS_H
#define NODEGLOBALS_H

#include <QVector2D>

#include "render/cancelatom.h"
#include "render/loopmode.h"
#include "render/videoparams.h"

namespace olive {

class ValueParams
{
public:
  ValueParams()
  {
  }

  ValueParams(const VideoParams &vparam, const AudioParams &aparam, const TimeRange &time, const QString &output, LoopMode loop_mode, CancelAtom *cancel) :
    video_params_(vparam),
    audio_params_(aparam),
    time_(time),
    loop_mode_(loop_mode),
    cancel_atom_(cancel),
    output_(output)
  {
  }

  ValueParams(const VideoParams &vparam, const AudioParams &aparam, const rational &time, const QString &output, LoopMode loop_mode, CancelAtom *cancel) :
    ValueParams(vparam, aparam, TimeRange(time, time + vparam.frame_rate_as_time_base()), output, loop_mode, cancel)
  {
  }

  QVector2D square_resolution() const { return video_params_.square_resolution(); }
  QVector2D nonsquare_resolution() const { return video_params_.resolution(); }
  const AudioParams &aparams() const { return audio_params_; }
  const VideoParams &vparams() const { return video_params_; }
  const TimeRange &time() const { return time_; }
  LoopMode loop_mode() const { return loop_mode_; }
  const QString &output() const { return output_; }

  CancelAtom *cancel_atom() const { return cancel_atom_; }
  bool is_cancelled() const { return cancel_atom_ && cancel_atom_->IsCancelled(); }

  ValueParams time_transformed(const TimeRange &time) const;
  ValueParams output_edited(const QString &output) const;

private:
  VideoParams video_params_;
  AudioParams audio_params_;
  TimeRange time_;
  LoopMode loop_mode_;
  CancelAtom *cancel_atom_;
  QString output_;

};

}

#endif // NODEGLOBALS_H
