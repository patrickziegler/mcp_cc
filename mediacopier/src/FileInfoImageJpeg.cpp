/* Copyright (C) 2020 Patrick Ziegler
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <mediacopier/AbstractFileOperation.hpp>
#include <mediacopier/Error.hpp>
#include <mediacopier/FileInfoImageJpeg.hpp>

namespace MediaCopier {

FileInfoImageJpeg::FileInfoImageJpeg(std::filesystem::path path, Exiv2::ExifData& exif) : FileInfoImage{std::move(path), exif}
{
    const auto& item = exif.findKey(Exiv2::ExifKey{"Exif.Image.Orientation"});

    if (item == exif.end()) {
        throw FileInfoImageJpegError{"Field 'Exif.Image.Orientation' not found in metadata"};
    }

    auto orientation = item->toLong();

    if (orientation < static_cast<long>(Orientation::ROT_0)) {
        throw FileInfoImageJpegError{"Invalid orientation value (smaller than min)"};
    }

    if (orientation > static_cast<long>(Orientation::ROT_90)) {
        throw FileInfoImageJpegError{"Invalid orientation value (bigger than max)"};
    }

    m_orientation = static_cast<Orientation>(orientation);
}

void FileInfoImageJpeg::accept(const AbstractFileOperation& operation) const
{
    operation.visit(*this);
}

} // namespace MediaCopier