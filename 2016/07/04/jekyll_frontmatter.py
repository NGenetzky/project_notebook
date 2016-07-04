# Import the os module, for the os.walk function
import os
import frontmatter
import slugify
import re
from datetime import datetime

YYYYMMDD = re.compile('\d{4}[-/]\d{2}[-/]\d{2}')

def from_date(datestr):
    for fmt in ('%Y-%m-%d', '%d.%m.%Y', '%d/%m/%y'):
        try:
            return datetime.strptime(datestr, fmt)
        except ValueError:
            pass
    raise ValueError('no valid date format found for "{0}"'.format(datestr))

class JPost:
    #Defaults
    defaults = {
        'layout':'single',
        'published':'true',
        'author':'"Nathan Genetzky"'
    }

    def __init__(self, fpath):
        self.srcpath = fpath
        self.post = frontmatter.load(self.srcpath)
        self.destpath = self.srcpath
        self.ext = os.path.splitext(self.srcpath)[1].strip().lower()

        self.remove_empty()
        if self.has_minimum():
            self.validate_date()
            self.post['title'] = str(self.post['title'])

            self.defaults['slug'] = self.slug()
            self.defaults['filename'] = self.filename()
            self.destpath = os.path.join('./_posts/', self.filename())

    def __str__(self):
        return frontmatter.dumps(self.post)

    def has_minimum(self):
        keys = self.post.keys()
        if("date" not in keys):
            return False
        if("title" not in keys):
            return False
        return True

    def slug(self):
        return slugify.slugify(self.post["title"], to_lower=True)

    def filename(self):
        return '{0}-{1}{2}'.format(self.post["date"], self.slug(), self.ext)

    def keys(self):
        return self.post.keys()

    def remove_empty(self):
        for k in self.keys():
            if(self.post[k] is None):
                 del self.post[k]

    def apply_defaults(self):
        keys = self.keys()
        for d in self.defaults:
            if d not in keys:
                self.post[d] = self.defaults[d]

    def write_file(self):
        with open(self.destpath, 'w') as f:
            text = frontmatter.dumps(self.post)
            f.write(unicode(text).encode('utf-8'))

    def validate_date(self):
        dateobj = self.post['date']
        # self.post['date'] = dateobj.strftime('%Y-%m-%d')
        self.post['date'] = str(dateobj.strftime('%Y-%m-%d'))

    def str_front_matter(self):
        fm = []
        for k in self.keys() :
            fm.append('{1}:{2}'.format(k, self.post.k))
        return '\n'.join(fm)


def filename_filter(filename):
    ext = os.path.splitext(filename)[1].strip().lower()
    if (YYYYMMDD.findall(filename)): # Ignores any files with YYYY-MM-DD
        return False
    if('.md' == ext):
        return True
    else:
        return False

def visit_dir(args, dirname, names):
    for fname in names:
        if not filename_filter(fname):
            continue
        fpath = os.path.join(dirname, fname)
        if os.path.isdir(fpath):
            continue
        jp = JPost(fpath)
        if not (jp.has_minimum()):
            print('Unable to handle {0}'.format(fpath))
            print(jp.str_front_matter())
            continue
        print('{0}->{1}'.format(fpath, jp.destpath))
        jp.apply_defaults()
        jp.write_file()

# Set the directory you want to start from
os.path.walk('.', visit_dir, "")

