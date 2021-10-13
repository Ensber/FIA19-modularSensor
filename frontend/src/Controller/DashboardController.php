<?php

namespace App\Controller;

use App\Entity\Platform;
use App\Exception\InputValidationException;
use App\Repository\PlatformRepository;
use App\Service\InputValidator;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Routing\Annotation\Route;
use Symfony\Component\HttpFoundation\Response;


class DashboardController extends AbstractController
{
    private $platformRepository;

    public function __construct(PlatformRepository $platformRepository){
        $this->platformRepository = $platformRepository;
    }
    /**
     * @Route("/dashboard", methods={"GET"}, name="dashboard")
     */
    public function dashboardAction(): Response{
        $platform = $this->platformRepository->findAll();
        return $this->render('dashboard/dashboard.html.twig', [
            "platform" => $platform
        ]);
    }

    /**
     * @ROUTE("/getEditPlatform/{platformId}")
     */
    public function getEditPlatformAction(string $platformId): JsonResponse{

        $platform = $this->platformRepository->findBy(['plId' => $platformId]);
        if ($platform !== []) {
            $platformFormated = $this->getFormatedEditPlatform($platform[0]);
        } else {
            return new JsonResponse(['status' => 'error'], 400);
        }
        return new JsonResponse(['status' => 'success', 'platform' => $platformFormated]);
    }

    private function getFormatedEditPlatform(Platform $platform): array{
        return [
            'id' => $platform->getPlId(),
            'name' => $platform->getName(),
            'abfrageInterval' => $platform->getAbfrageinterval()->format('H:i'),
            'farbe' => $platform->getFarbe()
        ];
    }

    /**
     * @ROUTE("/editPlatform", methods={"POST"}, name="editPlatform")
     */
    public function editPlatformAction(Request $request, InputValidator $inputValidator){
        try{
            $editDataDTO = $inputValidator->validateEditPlatformRequest($request);
        }catch (InputValidationException $e){
            return new JsonResponse(['status' => 'error', 'errors' => $e->getValidationErrors()], 400);
        }
        $platform = $this->platformRepository->findBy(['plId' => $editDataDTO->getId()]);
        $this->platformRepository->editPlatform($platform[0], $editDataDTO->getName(),
                                $editDataDTO->getFarbe(), $editDataDTO->getAbfrageinterval());
        return new JsonResponse(['status' => 'success']);
    }

    //TODO: Controller Edit Platform + DTO + validation Service + Repository Request
}