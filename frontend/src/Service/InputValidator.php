<?php

namespace App\Service;



use App\DTO\editPlatformDTO;
use App\DTO\getDataDTO;
use App\Exception\InputValidationException;
use App\Repository\PlatformRepository;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Validator\ConstraintViolationList;
use Symfony\Component\Validator\Validator\ValidatorInterface;

class InputValidator
{
    private ValidatorInterface $validator;
    private PlatformRepository $platformRepository;

    public function __construct(ValidatorInterface $validator, PlatformRepository $platformRepository){
        $this->validator = $validator;
        $this->platformRepository = $platformRepository;
    }

    public function validateDataRequest(Request $request): getDataDTO{
        $getDataDTO = new getDataDTO($request->request);
        $errors = $this->validator->validate($getDataDTO);

        $validationErrors = $this->extractValidationErrors($errors);

        if (count($errors) === 0){
            if ($getDataDTO->getEnd() <= $getDataDTO->getBegin()){
                $validationErrors['end'] = "Das Enddatum darf nicht kleiner oder gleich dem Startdatum sein!";
            }
        }
        if (!empty($validationErrors)){
            throw new InputValidationException($validationErrors);
        }

        return $getDataDTO;
    }

    public function validateEditPlatformRequest(Request $request){
        $editPlatformDTO = new editPlatformDTO($request->request);
        $errors = $this->validator->validate($editPlatformDTO);

        $validationErrors = $this->extractValidationErrors($errors);

        if (count($errors) === 0){
            $platform = $this->platformRepository->findBy(['plId' => $editPlatformDTO->getId()]);
            if($platform === []){
                $validationErrors['id'] = "Ungültige Platform Id";
            }
        }

        if(!empty($validationErrors)){
            throw new InputValidationException($validationErrors);
        }

        return $editPlatformDTO;
    }


    private function extractValidationErrors(ConstraintViolationList $errors): array
    {
        $validationErrors = [];
        foreach ($errors as $error) {
            $validationErrors[$error->getPropertyPath()] = $error->getMessage();
        }

        return $validationErrors;
    }

}