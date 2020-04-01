;;; strptime-tests.el --- Tests                      -*- lexical-binding: t; -*-

;; Copyright (C) 2020  Xu Chunyang

;; Author: Xu Chunyang

;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <https://www.gnu.org/licenses/>.

;;; Commentary:

;; Tests for strptime.el

;;; Code:

(require 'strptime)
(require 'ert)

(ert-deftest strptime ()
  (should (equal (strptime "2020-04-01" "%Y-%m-%d")
                 '(0 0 0 1 4 2020 3 nil 0)))

  (should (equal (strptime "2020-04-01T07:39:26+0800" "%FT%T%z")
                 '(26 39 7 1 4 2020 3 nil 28800)))

  (should-error (strptime "2020-04-XX" "%Y-%m-%d")))

(provide 'strptime-tests)
;;; strptime-tests.el ends here
