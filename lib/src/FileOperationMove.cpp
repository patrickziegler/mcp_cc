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

#include <mediacopier/FileInfoImage.hpp>
#include <mediacopier/FileInfoImageJpeg.hpp>
#include <mediacopier/FileInfoVideo.hpp>
#include <mediacopier/FileOperationMove.hpp>

namespace fs = std::filesystem;
namespace mc = MediaCopier;

void mc::FileOperationMove::visit(const mc::FileInfoImage &file) const
{
    copyFile(file);
    fs::remove(file.path());
}

void mc::FileOperationMove::visit(const mc::FileInfoImageJpeg &file) const
{
    copyFile(file);
    fs::remove(file.path());
}

void mc::FileOperationMove::visit(const mc::FileInfoVideo &file) const
{
    copyFile(file);
    fs::remove(file.path());
}
