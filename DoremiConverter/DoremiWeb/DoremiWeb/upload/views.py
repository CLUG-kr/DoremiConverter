from django.shortcuts import render

# Create your views here.
def upload_file(request):
    return render(request, 'upload/upload_file.html', {})
